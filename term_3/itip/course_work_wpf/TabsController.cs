using Microsoft.Web.WebView2.WinForms;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace course_work_wpf
{
    // THIS CONTAINS BUG: list of tabs should be 
    // added to call their destructors on tab
    // close. Now tabs with media player will 
    // stop playback only on window termination
    public class TabsController
    {
        public int TabsCount = 0;
        TabControl tbCtrl;
        public TabsController(TabControl tbctrl)
            => tbCtrl = tbctrl;
        public void AddNewTab(string link = "http://google.com")
        {
            if (TabsCount == 5)
            {
                MessageBox.Show("Too many tabs open.");
                return;
            }
            TabsCount++;

            Tab tab = new(link);
            Grid tabContentGrid = new();
            tabContentGrid.Children.Add(tab.TextBoxQuery);
            tabContentGrid.Children.Add(tab.ButtonGoBack);
            tabContentGrid.Children.Add(tab.ButtonGoForward);
            tabContentGrid.Children.Add(tab.ButtonReload);
            tabContentGrid.Children.Add(tab.ButtonAddToFavourites);
            tabContentGrid.Children.Add(tab.WV);

            StackPanel hdr = new();
            hdr.Orientation = Orientation.Horizontal;
            Label LabelClose = new()
            {
                Content = "x"
            };
            LabelClose.MouseDown += LabelClose_MouseDown;

            hdr.Children.Add(tab.LabelCurrentUrl);
            hdr.Children.Add(LabelClose);

            TabItem newTabItem = new()
            {
                Header = hdr,
                Content = tabContentGrid
            };

            tbCtrl.Items.Add(newTabItem);
        }
        private void LabelClose_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            if (tbCtrl.SelectedIndex == 0) return;
            tbCtrl.Items.RemoveAt(tbCtrl.SelectedIndex);
            TabsCount--;
            // BUG: deleting the tab object is necessary
        }
    }
}
