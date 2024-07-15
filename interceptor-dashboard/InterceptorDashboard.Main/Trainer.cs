using InterceptorDashboard.Models;
using Microsoft.ML;

namespace InterceptorDashboard.Main;

public class Trainer
{
    private readonly MLContext _context = new();
    
    public DataOperationsCatalog.TrainTestData LoadDataFromCsv(string dataPath, double testFraction)
    {
        var data = _context.Data.LoadFromTextFile<FlightData>(dataPath, separatorChar: ',', hasHeader: true);
        data = _context.Data.ShuffleRows(data);

        return _context.Data.TrainTestSplit(data, testFraction: testFraction);
    }
    
    public ITransformer BuildPipelineAndTrain(IDataView trainSet)
    {
        var pipeline = _context.Transforms.Concatenate("Features",
                nameof(FlightData.Throttle),
                nameof(FlightData.Yaw),
                nameof(FlightData.Pitch),
                nameof(FlightData.Roll))
            //.Append(_context.Transforms.NormalizeMinMax("Features"))
            .Append(_context.BinaryClassification.Trainers.LdSvm(nameof(FlightData.Legitimate)));

        return pipeline.Fit(trainSet);
    }

    public void EvaluateAndPrintMetrics(ITransformer model, IDataView testSet)
    {
        var predictions = model.Transform(testSet);
        var metrics = _context.BinaryClassification.EvaluateNonCalibrated(predictions, nameof(FlightData.Legitimate));
        
        Console.WriteLine($"Accuracy: {metrics.Accuracy:P2}");
        Console.WriteLine($"F1 Score: {metrics.F1Score:P2}");
        Console.WriteLine($"Area under ROC curve: {metrics.AreaUnderRocCurve:P2}");
    }

    public void SaveModel(ITransformer model, IDataView data, string path)
    {
        _context.Model.Save(model, data.Schema, path); 
    }
}