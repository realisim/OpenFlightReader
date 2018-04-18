using CppSharp;

namespace OpenFlight.CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            ConsoleDriver.Run(new OpenFlightLibrary());
        }
    }
}