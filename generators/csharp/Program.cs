using CommandLine;
using CppSharp;

namespace OpenFlight.CSharp
{

    internal class Options
    {
        [Option('L', "LIB_PATH", Required = true, HelpText = "Library directory path")]
        public string LibraryDirectoryPath { get; set; }

        [Option('I', "INCLUDE_PATH", Required = true, HelpText = "Include directory path")]
        public string IncludeDirectoryPath { get; set; }

        [Option('l', "lib_filename", Required = true, HelpText = "Library filename")]
        public string LibFilename { get; set; }

        [Option('i', "header_filename", Required = true, HelpText = "Header filename")]
        public string HeaderFilename { get; set; }

        [Option('o', "outdir", Required = false, HelpText = "Output directory path")]
        public string OutputDirectoryPath { get; set; }
    }

    class Program
    {
        static void HandleParseError(System.Collections.Generic.IEnumerable<Error> errs)
        {
            System.Console.WriteLine("ERR: Type --help for more informations.");
        }

        static void RunOptionsAndReturnExitCode(Options opts)
        {
            ConsoleDriver.Run(new OpenFlightLibrary()
            {
                LibDirectoryPath     = opts.LibraryDirectoryPath,
                LibFilename          = opts.LibFilename,
                IncludeDirectoryPath = opts.IncludeDirectoryPath,
                HeaderFilename       = opts.HeaderFilename,
                OutputDirectoryPath = (opts.OutputDirectoryPath != null) ? opts.OutputDirectoryPath : ""
            });
        }

        static void Main(string[] rawArgs)
        {
            CommandLine.Parser.Default.ParseArguments<Options>(rawArgs)
            .WithParsed<Options>(opts => RunOptionsAndReturnExitCode(opts))
            .WithNotParsed<Options>((errs) => HandleParseError(errs));          
        }
    }
}