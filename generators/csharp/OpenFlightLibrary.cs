using CppSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CppSharp.AST;
using CppSharp.Generators;

namespace OpenFlight.CSharp
{
    class OpenFlightLibrary : ILibrary
    {
        public string LibDirectoryPath = "";
        public string IncludeDirectoryPath = "";

        public string LibFilename = "";
        public string HeaderFilename = "";

        public string OutputDirectoryPath = "";

        public void Postprocess(Driver driver, ASTContext ctx)
        {
        }

        public void Preprocess(Driver driver, ASTContext ctx)
        {
        }

        public void Setup(Driver driver)
        {
            
            /*driver.ParserOptions.UnityBuild = true;
            driver.ParserOptions.MicrosoftMode = true;
            driver.ParserOptions.TargetTriple = "OpenFlightReader";
            driver.ParserOptions.Abi = CppSharp.Parser.AST.CppAbi.Itanium;  */     

            var options = driver.Options;
            options.GeneratorKind = GeneratorKind.CSharp;

            if (!string.IsNullOrEmpty(OutputDirectoryPath))
                options.OutputDir = OutputDirectoryPath;

            //options.CheckSymbols = true;
            //options.CompileCode = true;
            //options.GenerateDefaultValuesForArguments = true;
            //options.MarshalCharAsManagedChar = true;
            //options.CommentKind = CommentKind.BCPLSlash;

            var module = driver.Options.AddModule("OpenFlightReader");
            module.IncludeDirs.Add(IncludeDirectoryPath);
            module.Headers.Add(HeaderFilename);
            module.LibraryDirs.Add(LibDirectoryPath);
            module.Libraries.Add(LibFilename);
            
        }

        public void SetupPasses(Driver driver)
        {
        }
    }
}
