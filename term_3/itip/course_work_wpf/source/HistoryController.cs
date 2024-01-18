using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Xml.Serialization;

namespace course_work_wpf
{
    public class HistoryController
    {
        public const string HistoryCsvPath = "\\\\Mac\\Home\\Documents\\practices\\term_3\\itip\\course_work_wpf\\Resources\\history.csv";
        public ListView LV;
        public List<HistoryItem> ListHistory;
        public HistoryController(ListView lV)
        {
            LV = lV;
            ListHistory = new List<HistoryItem>();
            InitUI();
            LoadFromFile(HistoryCsvPath);
            if (ListHistory.Count != 0)
                foreach (HistoryItem item in ListHistory)
                    AddToHistory(item, false);
        }
        private void InitUI()
        {
            GridView gv = new GridView();
            gv.Columns.Add(new GridViewColumn { Header = "Link", DisplayMemberBinding = new Binding("Link"), Width = 200 });
            gv.Columns.Add(new GridViewColumn { Header = "Visit time", DisplayMemberBinding = new Binding("TimeVisited") });
            LV.View = gv;
            LV.ContextMenu = new();

            MenuItem RemoveMi = new MenuItem { Header = "Remove" };
            RemoveMi.Click += RemoveMi_Click;
            LV.ContextMenu.Items.Add(RemoveMi);

            MenuItem OpenMi = new MenuItem { Header = "Open" };
            OpenMi.Click += OpenMi_Click;
            LV.ContextMenu.Items.Add(OpenMi);
        }
        private void RemoveMi_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (LV.SelectedItem == null) return;

            HistoryItem item = (HistoryItem)LV.SelectedItem;
            LV.Items.Remove(LV.SelectedItem);
            ListHistory.Remove(item);

            SaveToFile(HistoryCsvPath);
        }
        private void OpenMi_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (LV.SelectedItem == null) return;
            MainWindow wnd = (MainWindow)Application.Current.MainWindow;

            HistoryItem item = (HistoryItem)LV.SelectedItem;
            wnd.tabsController.AddNewTab(item.Link);
        }
        public void AddToHistory(HistoryItem item, bool _new = true)
        {
            LV.Items.Insert(0, item);
            if (_new)
            {
                ListHistory.Insert(0, item);
                SaveToFile(HistoryCsvPath);
            }
        }
        public void LoadFromFile(string filePath)
        {
            using (StreamReader sr = new(filePath))
                while (!sr.EndOfStream)
                {
                    string[] row = sr.ReadLine().Split(',');
                    HistoryItem item = new(row[0], row[1]);
                    ListHistory.Add(item);
                }
        }
        public void SaveToFile(string filePath)
        {
            using (StreamWriter sr = new StreamWriter(filePath))
                foreach (HistoryItem item in ListHistory)
                    sr.WriteLine(item.Link + "," + item.TimeVisited);
        }
        public void ClearHistory()
        {
            LV.Items.Clear();
            ListHistory.Clear();
            SaveToFile(HistoryCsvPath);
        }
    }
}
