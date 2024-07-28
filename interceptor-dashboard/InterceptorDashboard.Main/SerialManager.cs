using System.IO.Ports;
using InterceptorDashboard.Models;

// ReSharper disable ConvertToPrimaryConstructor

namespace InterceptorDashboard.Main;

public class SerialManager
{
    private readonly SerialPort _serialPort;

    private CancellationTokenSource _readCts;

    public SerialManager(string portName, int baudRate = 115200)
    {
        _serialPort = new SerialPort(portName, baudRate);
        _serialPort.DataBits = 8;
        _serialPort.Parity = Parity.None;
        _serialPort.StopBits = StopBits.One;
        _serialPort.Handshake = Handshake.None;

        _readCts = new CancellationTokenSource();
    }

    public void OpenConnection()
    {
        _serialPort.Open();
    }

    public void CloseConnection()
    {
        _serialPort.Close();
    }

    public async Task StartRead(SerialManagerDataReceived d)
    {
        await Task.Run(() =>
        {
            while (!_readCts.IsCancellationRequested)
            {
                var data = _serialPort.ReadLine();
                d?.Invoke(data);
            }
        });
    }

    /// <summary>
    /// Cancels the read operation running on the thread pool
    /// </summary>
    public async Task StopRead()
    {
        await _readCts.CancelAsync();
    }
    
    /// <summary>
    /// Logs all available serial ports
    /// </summary>
    public static void LogAvailablePorts()
    {
        Console.WriteLine("Logging available ports...");
        var ports = SerialPort.GetPortNames();

        foreach (var port in ports)
        {
            Console.WriteLine($"Port: {port}");
        }
    }

    public static FlightData ParseToFlightData(string data)
    {
        var parts = data.Split(",");
        var pitch = float.Parse(parts[0]);
        var roll = float.Parse(parts[1]);
        var yaw = float.Parse(parts[2]);
        var throttle = float.Parse(parts[3]);

        return new FlightData()
        {
            Throttle = throttle,
            Yaw = yaw,
            Pitch = pitch,
            Roll = roll
        };
    }
}