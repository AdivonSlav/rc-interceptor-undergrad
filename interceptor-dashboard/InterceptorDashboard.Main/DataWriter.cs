using System.Collections.Concurrent;
using System.Globalization;
using System.Text;
using InterceptorDashboard.Models;

// ReSharper disable InvertIf

namespace InterceptorDashboard.Main;

public class DataWriter(string filePath)
{
    private readonly CancellationTokenSource _writeCts = new();
    private readonly BlockingCollection<FlightData> _writeQueue = new();
    private Task? _writingTask;
    
    private const int FlushThreshold = 15;

    public void EnqueueData(FlightData data)
    {
        _writeQueue.Add(data);
    }

    /// <summary>
    /// Starts a task on the thread pool that will write data from the internal write queue to disk
    /// </summary>
    public void StartWriting()
    {
        _writingTask = Task.Run((ProcessQueue));
    }

    /// <summary>
    /// Signals the worker to stop writing. The worker will attempt to write any remaning data in the queue first before shutting down
    /// </summary>
    public void StopWriting()
    {
        _writeCts.Cancel();
        _writeQueue.CompleteAdding();

        // Wait for the task to finish and ignore the cancellation exception (for now, probably redundant)
        try
        {
            _writingTask!.Wait();
        } catch (AggregateException ex) when (ex.InnerExceptions[0] is OperationCanceledException) {}
    }

    private void ProcessQueue()
    {
        using var sw = new StreamWriter(filePath, true, Encoding.UTF8);
        var writesPending = 0;

        while (!_writeCts.IsCancellationRequested || !_writeQueue.IsCompleted)
        {
            if (_writeQueue.TryTake(out var data))
            {
                var csv = FormatAsCsv(data);

                sw.WriteLine(csv);
                writesPending++;

                if (writesPending == FlushThreshold)
                {
                    sw.Flush();
                    writesPending = 0;
                }
            }
        }
        
        // Process remaining enqueued data
        while (_writeQueue.TryTake(out var data))
        {
            var csv = FormatAsCsv(data);
            sw.WriteLine(csv);
            sw.Flush();
        }
    }

    private static string FormatAsCsv(FlightData data)
    {
        var timestamp = DateTime.Now.ToString(CultureInfo.InvariantCulture);
        var csv = $"{timestamp},{data.Throttle},{data.Yaw},{data.Pitch},{data.Roll},{data.Legitimate}";

        return csv;
    }
}