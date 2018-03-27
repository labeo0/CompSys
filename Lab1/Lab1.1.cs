using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Globalization;
using System.Threading;

namespace Lab1._1CS_cs
{
    class Program
    {
        static void Main(string[] args)
        {
            double H = 0;//entropy
            int info = 0;//info quantity
            //string path = @"D:\1LABS\course3.2\LabComputerSystems\Lab1.1CS_cs\txt\13Base64.txt";
            //string path = @"D:\1LABS\course3.2\LabComputerSystems\Lab1.1CS_cs\txt\RepkaBase64.txt";
            //string path = @"D:\1LABS\course3.2\LabComputerSystems\Lab1.1CS_cs\txt\GPLv2Base64.txt";
            string path = @"D:\1LABS\course3.2\LabComputerSystems\Lab1.1CS_cs\txt\GPLv2Base64.tar.bz";
            string text = "";
            double len = 0.0;
            Console.OutputEncoding = Encoding.UTF8;
            using (StreamReader sr = new StreamReader(path, Encoding.UTF8))
            {
                text = sr.ReadToEnd();
                sr.Close();
            }
            //Console.WriteLine(text);
            len = text.Length;
            Dictionary<char, int> pair = new Dictionary<char, int>();
            double CountSym = 0;
            foreach (char c in text)
            {
                if (pair.ContainsKey(c))
                    pair[c] += 1;
                else
                {
                    pair.Add(c, 1);
                    CountSym++;
                }
            }
            foreach (var item in pair)
            {
                H -= (item.Value / len) * Math.Log(item.Value / len, 2);
                Console.WriteLine("Symbol: " + item.Key + " Frequency: " + item.Value + " Probability: " + item.Value / len + " \n");
            }
            Console.WriteLine("Entropy bit: " + H + "\n" + "Info quantity byte: " + H * CountSym / 8);
            FileInfo file = new FileInfo(path);
            Console.WriteLine("File name:  "+file.Name+" File size byte: "+ file.Length);
            Console.WriteLine(len);
        }
    }
}
