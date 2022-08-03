class MyCalendar {
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        if(!bookings.size()) {
            bookings.push_back({start,end});
            return true;
        }
        
        int l=0, r=bookings.size()-1;
        int mid = l+(r-l)/2;
        
        while(l <= r) {
            mid = l+(r-l)/2;
            
            std::pair <int,int> current = bookings[mid];
            if((start >= current.first && start < current.second) || (end > current.first && end < current.second) || (start < current.first && end >= current.second)) {
                return false;
            } else if(start >= current.second) l = mid+1;
            else r = mid-1;
        }
        
        bookings.push_back({start,end});
        std::sort(bookings.begin(), bookings.end());
        return true;
    }
    
private:
    std::vector <std::pair<int,int>> bookings;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
