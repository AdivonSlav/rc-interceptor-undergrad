using InterceptorDashboard.Main;
using InterceptorDashboard.Models;

const string modelPath = "ldsvm_flightdata_model.zip";

if (args.Contains("--train"))
{
    var trainer = new Trainer();
    Console.WriteLine("Loading data from CSV...");
    var splitData = trainer.LoadDataFromCsv("Data/drone_flight_data.csv", 0.2);
    
    Console.WriteLine("Building pipeline and training model...");
    var model = trainer.BuildPipelineAndTrain(splitData.TrainSet);
    
    trainer.EvaluateAndPrintMetrics(model, splitData.TestSet);
    trainer.SaveModel(model, splitData.TrainSet, modelPath);
    Environment.Exit(0);
}

// Initialize stuff
var dataWriter = new DataWriter("data.csv");
var serialManager = new SerialManager("/dev/ttyACM0");
var predictor = new Predictor();

// Load model for predictions
predictor.LoadModel(modelPath);

SerialManagerDataReceived handler = data =>
{
    var asFlightData = SerialManager.ParseToFlightData(data);
    var prediction = predictor.MakePrediction(asFlightData);

    asFlightData.Legitimate = prediction.LegitimatePrediction;
    dataWriter.EnqueueData(asFlightData);
    
    Console.WriteLine($"Received: {data}  ->  Usage was {prediction.LegitimatePrediction}");
};

// Read and write phase
Console.WriteLine("Starting worker to start reading from COM port...");
serialManager.OpenConnection();
_ = serialManager.StartRead(handler);

Console.WriteLine("Starting worker to begin writes...");
dataWriter.StartWriting();

// Termination phase
var key = Console.ReadKey();
if (key.Key == ConsoleKey.Enter)
{
    await serialManager.StopRead();
    dataWriter.StopWriting();
    
    serialManager.CloseConnection();
}


