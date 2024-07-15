using Microsoft.ML.Data;

namespace InterceptorDashboard.Models;

public class FlightData
{
    [LoadColumn(0)]
    public float Throttle { get; set; }
    
    [LoadColumn(1)]
    public float Yaw { get; set; }
    
    [LoadColumn(2)]
    public float Pitch { get; set; }
    
    [LoadColumn(3)]
    public float Roll { get; set; }
    
    [LoadColumn(4)]
    public bool Legitimate { get; set; }
}

public class FlightPrediction : FlightData
{
    [ColumnName("PredictedLabel")]
    public bool LegitimatePrediction { get; set; }
    
    public float Probability { get; set; }
    
    public float Score { get; set; }
}