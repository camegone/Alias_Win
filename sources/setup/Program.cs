// See https://aka.ms/new-console-template for more information
using System;
using System.Collections;
using System.IO;

namespace Camegone.AliasWin.Setup{
    public class Setup{
        static void AddToUserPath(string path)
        {
            bool flag = false;
            string userPathStr = Environment.GetEnvironmentVariable("Path", EnvironmentVariableTarget.User);
            var userPathList = new List<string>(userPathStr.Split(';'));
            if (! userPathList.Contains(path) )
            {
                userPathList.Add(path);
                Environment.SetEnvironmentVariable("Path", string.Join(";", userPathList), EnvironmentVariableTarget.User);
                Console.WriteLine("Added to user path.");
            } else {
                Console.WriteLine("Already exists in user path.");
            }
        }

        static string GetUserRootDirectory()
        {
            string userRoot = Environment.GetEnvironmentVariable("USERPROFILE");
            //Console.WriteLine(userRoot);
            return userRoot;
        }
        
        static void EnsureDirectory(string path)
        {
            if (! Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
                Console.WriteLine($"Created {path}.");
            } else {
                Console.WriteLine($"{path} exists.");
            }
        }

        static void Install(string installDir, string[] fileNames)
        {
            foreach (string file in fileNames)
            {
                string path = $@"{installDir}\{file}";
                if (File.Exists(path))
                {
                    Console.WriteLine($"{path} already exists. overwrite it.");
                    File.Copy(file, path, true);
                } else {
                    Console.WriteLine($"Copying {file} into {path}.");
                    File.Copy(file, path); 
                }
            }
        }

        static void Main()
        {
            var _fileNames = new string[] { "walias.exe", "unwalias.exe" };

            //get the properties
            var root = GetUserRootDirectory();
            string path = $"{root}\\Aliases";

            //setup path
            Console.WriteLine($"Set up {path} in your User Variable.");
            EnsureDirectory(path);
            AddToUserPath(path);
            
            //copy the programs
            Console.WriteLine($"Install programs to {path}");
            Install(path, _fileNames);

            Console.WriteLine("Installation complete.");
            Console.Read();
        }
    }
}
