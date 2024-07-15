using InterceptorDashboard.Models;
using Microsoft.ML;

namespace InterceptorDashboard.Main;

public class Predictor
{
    private readonly MLContext _context = new();

    private DataViewSchema? _modelSchema;
    private ITransformer? _model;

    public void LoadModel(string path)
    {
        _model = _context.Model.Load(path, out _modelSchema);
    }

    public FlightPrediction MakePrediction(FlightData input)
    {
        var predictionEngine = _context.Model.CreatePredictionEngine<FlightData, FlightPrediction>(_model);
        return predictionEngine.Predict(input);
    }
}