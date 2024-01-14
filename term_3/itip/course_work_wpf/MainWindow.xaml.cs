using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace course_work_wpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public TabsController tabsController;
        public FavouritesController favouritesController;
        public HistoryController historyController;
        public MainWindow()
        {
            InitializeComponent();
            tabsController = new(TabControlMain);
            favouritesController = new(ListViewFavourites);
            historyController = new(ListViewHistory);
        }

        private void ButtonAddNewTab_Click(object sender, RoutedEventArgs e)
        {
            tabsController.AddNewTab();   
        }
        private void TabControlMain_Loaded(object sender, RoutedEventArgs e)
        {
            TabControlMain = sender as TabControl;
        }
        private void ListViewFavourites_Loaded(object sender, RoutedEventArgs e)
        {
            ListViewFavourites = sender as ListView;
        }
        private void ListViewHistory_Loaded(object sender, RoutedEventArgs e)
        {
            ListViewHistory = sender as ListView;
        }
        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {
            historyController.ClearHistory();
        }
    }
}