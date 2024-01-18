using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace course_work_wpf
{
    public struct FavouritesItem
    {
        public string Link { get; set; }
        public string Title { get; set; }
        public FavouritesItem() { Link = ""; Title = ""; }
        public FavouritesItem(string l, string t) { Link = l; Title = t; }
    }
}
