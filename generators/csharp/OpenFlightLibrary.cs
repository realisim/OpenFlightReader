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
            //options.CheckSymbols = true;
            //options.CompileCode = true;
            //options.GenerateDefaultValuesForArguments = true;
            //options.MarshalCharAsManagedChar = true;
            //options.CommentKind = CommentKind.BCPLSlash;

            var module = driver.Options.AddModule("OpenFlightReader");
            module.IncludeDirs.Add(@"F:\Git\OpenFlightReader\bin\include");
            module.Headers.Add("OpenFlightReader.h");
            module.LibraryDirs.Add(@"F:\Git\OpenFlightReader\bin\dll");
            module.Libraries.Add("OpenFlightReader.lib");
            
        }

        public void SetupPasses(Driver driver)
        {
        }
    }
}
