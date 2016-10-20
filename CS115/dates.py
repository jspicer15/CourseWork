#
# dates.py
#
# name:
#

class Date:
    """ a user-defined data structure that
        stores and manipulates dates
    """

    # the constructor is always named __init__ !
    def __init__(self, month, day, year):
        """ the constructor for objects of type Date """
        self.month = month
        self.day = day
        self.year = year


    # the "printing" function is always named __repr__ !
    def __repr__(self):
        """ This method returns a string representation for the
            object of type Date that calls it (named self).

             ** Note that this _can_ be called explicitly, but
                it more often is used implicitly via the print
                statement or simply by expressing self's value.
        """
        s =  "%02d/%02d/%04d" % (self.month, self.day, self.year)
        return s


    # here is an example of a "method" of the Date class:
    def isLeapYear(self):
        """ Returns True if the calling object is
            in a leap year; False otherwise. """
        if self.year % 400 == 0: return True
        elif self.year % 100 == 0: return False
        elif self.year % 4 == 0: return True
        return False

    def copy(self):
        """ Returns a new object with the same month, day, year
            as the calling object (self).
        """
        dnew = Date(self.month, self.day, self.year)
        return dnew

    def equals(self, d2):
        """ Decides if self and d2 represent the same calendar date,
            whether or not they are the in the same place in memory.
        """
        return self.year == d2.year and self.month == d2.month and self.day == d2.day

    def tomorrow(self):
        DIM = [0,31,28,31,30,31,30,31,31,30,31,30,31]
        self.day += 1
        if self.isLeapYear():
            DIM[2] = 29
        if self.day > DIM[self.month]:
            self.day = 1
            if self.month == 12:
                self.month = 1
                self.year += 1
            else:
                self.month += 1
        return self

    def yesterday(self):
        DIM = [0,31,28,31,30,31,30,31,31,30,31,30,31]
        self.day -= 1
        if self.isLeapYear():
            DIM[2] = 29
        if self.day < 1:
            self.day = DIM[self.month-1]
            if self.month == 1:
                self.month = 12
                self.year -= 1
            else:
                self.month -= 1
        return self

    def addNDays(self,N):
        i = 0
        print self
        while i < N:
            self.tomorrow()
            print self
            i += 1

    def subNDays(self,N):
        i = 0
        print self
        while i < N:
            self.yesterday()
            print self
            i += 1
        
    def isBefore(self,d2):
        if self.year < d2.year:
            return True
        elif self.year == d2.year:
            if self.month < d2.month:
                return True
            elif self.month == d2.month:   
                if self.day < d2.day:
                    return True
        else:
            return False

    def isAfter(self,d2):
        if self.equals(d2):
            return False
        elif self.isBefore(d2):
            return False
        else:
            return True
        
    def diff(self,d2):
        if self.equals(d2):
            return 0
        date1 = self.copy()
        date2 = d2.copy()
        days = 0
        while date1.equals(date2) == False:
            if date1.isBefore(date2):
                date1.tomorrow()
                days -= 1
            else:
                date2.tomorrow()
                days += 1
        return days
            
    def dow(self):
        DOW = ['Wednesday','Thursday','Friday','Saturday',"Sunday","Monday","Tuesday"]
        known = 3
        kdate = Date(11,9,2011)
        day = self.diff(kdate) 
        days = day % 7
        print days
        return DOW[days]
        
