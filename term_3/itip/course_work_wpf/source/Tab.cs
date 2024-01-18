using Microsoft.Web.WebView2.Core;
using Microsoft.Web.WebView2.WinForms;
using Microsoft.Web.WebView2.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace course_work_wpf
{
    class Tab
    {
        public Label LabelCurrentUrl;
        public TextBox TextBoxQuery;
        public Button ButtonGoBack;
        public Button ButtonGoForward;
        public Button ButtonReload;
        public Button ButtonAddToFavourites;
        public Microsoft.Web.WebView2.Wpf.WebView2 WV;
        public Tab(string link)
        {
            InitWV(link);
            InitUI();
        }
        private void InitUI()
        {
            LabelCurrentUrl = new Label();

            TextBoxQuery = new TextBox
            {
                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Top,
                MinWidth = 200,
                Width = 500,
                Margin = new Thickness(200, 0, 0, 0)
            };
            TextBoxQuery.KeyDown += TextBoxQuery_KeyDown;

            ButtonGoBack = new Button
            {
                Content = "Back",
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Left,
                Width = 60,
                Margin = new Thickness(5, 0, 0, 0),
            };
            ButtonGoBack.Click += ButtonGoBack_Click;

            ButtonGoForward = new Button
            {
                Content = "Forward",
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Left,
                Width = 60,
                Margin = new Thickness(70, 0, 0, 0)
            };
            ButtonGoForward.Click += ButtonGoForward_Click;

            ButtonReload = new Button
            {
                Content = "Reload",
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Left,
                Width = 60,
                Margin = new Thickness(135, 0, 0, 0)
            };
            ButtonReload.Click += ButtonReload_Click;

            ButtonAddToFavourites = new Button
            {
                Content = "Add to favourites",
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Right,
                Margin = new Thickness(0, 0, 5, 0)
            };
            ButtonAddToFavourites.Click += ButtonAddToFavourites_Click;
        }
        private async void InitWV(string link)
        {
            WV = new Microsoft.Web.WebView2.Wpf.WebView2
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(0, 25, 0, 0)
            };
            WV.NavigationCompleted += WV_NavigationCompleted;
            WV.SourceChanged += WV_SourceChanged;

            if (!link.Contains("https://") && !link.Contains("http://"))
                link = "http://" + link;

            try { WV.Source = new Uri(link); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
            await WV.EnsureCoreWebView2Async(null);
        }
        private void ButtonGoBack_Click(object sender, RoutedEventArgs e)
        {
            try { WV.GoBack(); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }
        private void ButtonGoForward_Click(object sender, RoutedEventArgs e)
        {
            try { WV.GoForward(); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }
        private void ButtonReload_Click(object sender, RoutedEventArgs e)
        {
            try { WV.Reload(); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }
        private void ButtonAddToFavourites_Click(object sender, RoutedEventArgs e)
        {
            MainWindow wnd = (MainWindow)Application.Current.MainWindow;

            FavouritesItem item = new(WV.Source.ToString(), WV.Source.Host.Replace("www.", ""));
            wnd.favouritesController.AddToFavourites(item);
            ButtonAddToFavourites.IsEnabled = false;
        }
        private void WV_SourceChanged(object? sender, CoreWebView2SourceChangedEventArgs e)
        {
            try { TextBoxQuery.Text = WV.Source.ToString(); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
            ButtonAddToFavourites.IsEnabled = true;
        }
        private void WV_NavigationCompleted(object sender, Microsoft.Web.WebView2.Core.CoreWebView2NavigationCompletedEventArgs e)
        {
            try { LabelCurrentUrl.Content = WV.Source.Host; }
            catch (Exception ex) { MessageBox.Show(ex.Message); }

            MainWindow wnd = (MainWindow)Application.Current.MainWindow;
            HistoryItem item = new(WV.Source.ToString(), DateTime.Now.ToString());
            wnd.historyController.AddToHistory(item);
        }
        private void TextBoxQuery_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key != Key.Enter) return;

            string url = TextBoxQuery.Text;
            if (!url.Contains("https://") && !url.Contains("http://"))
                url = "http://" + url;

            try { WV.Source = new Uri(url); }
            catch (Exception ex) { MessageBox.Show(ex.Message); }
        }
    }
}
