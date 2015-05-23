using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;

using PerforceAssist;

namespace PerforceTestCSharp
{
    public partial class MainWindow : Window
    {
        static string _username = "sami";
        static string _password = "";
        /*static string __workspaceName = "TestWorkSpace";
        static string _port = "localhost:1666";
        static string _host = "Sami";
        static string _depotName = "//data/...";
        static string _depotPath = "//data/...";
        static string _changelist = "32";
        static string _workspaceRoot = "";*/

        public MainWindow()
        {
            InitializeComponent();

            P4Task task = new P4Task();
            if (task.connect(_username, _password))
            {
                P4InfoCommand cmd = new P4InfoCommand();
                if (cmd.run(task))
                {
                    P4Info info = cmd.getInfo();
                    Debug.WriteLine(String.Format("Connected {0} successfully!", info.serverAddress));
                }
            }                
        }
    }
}