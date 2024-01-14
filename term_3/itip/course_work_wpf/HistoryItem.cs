using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace course_work_wpf
{
    public struct HistoryItem
    {
        public string Link { get; set; }
        public DateTime TimeVisited { get; set; }
        public HistoryItem() { Link = ""; TimeVisited = DateTime.Now; }
        public HistoryItem(string l, string t) 
        {
            Link = l;
            TimeVisited = DateTime.Parse(t);
        }
    }
}
