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
    public class FavouritesController
    {
        public const string FavouritesCsvPath = "\\\\Mac\\Home\\Documents\\practices\\term_3\\itip\\course_work_wpf\\Resources\\favourites.csv";
        public ListView LV;
        public List<FavouritesItem> ListFav;
        public FavouritesController(ListView lV)
        {
            LV = lV;
            ListFav = new List<FavouritesItem>();

            InitUI();
            LoadFromFile(FavouritesCsvPath);

            if (ListFav.Count != 0)
                foreach (FavouritesItem item in ListFav)
                    AddToFavourites(item, false);
        }
        private void InitUI()
        {
            GridView gv = new GridView();
            gv.Columns.Add(new GridViewColumn { Header = "Link", DisplayMemberBinding = new Binding("Link"), Width = 200 });
            gv.Columns.Add(new GridViewColumn { Header = "Title", DisplayMemberBinding = new Binding("Title") });
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
            FavouritesItem item = (FavouritesItem)LV.SelectedItem;
            LV.Items.Remove(LV.SelectedItem);
            ListFav.Remove(item);
            SaveToFile(FavouritesCsvPath);
        }
        private void OpenMi_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (LV.SelectedItem == null) return;
            MainWindow wnd = (MainWindow)Application.Current.MainWindow;
            FavouritesItem item = (FavouritesItem)LV.SelectedItem;
            wnd.tabsController.AddNewTab(item.Link);
        }
        public void AddToFavourites(FavouritesItem item, bool _new = true)
        {
            LV.Items.Insert(0, item);
            if (_new)
            {
                ListFav.Insert(0, item);
                SaveToFile(FavouritesCsvPath);
            }
        }
        public void LoadFromFile(string filePath)
        {
            using (StreamReader sr = new StreamReader(filePath))
                while (!sr.EndOfStream)
                {
                    string[] row = sr.ReadLine().Split(',');
                    FavouritesItem item = new FavouritesItem(row[0], row[1]);
                    ListFav.Add(item);
                }
        }
        public void SaveToFile(string filePath)
        {
            using (StreamWriter sr = new StreamWriter(filePath))
                foreach (FavouritesItem item in ListFav)
                    sr.WriteLine(item.Link + "," + item.Title);
        }
    }
}
