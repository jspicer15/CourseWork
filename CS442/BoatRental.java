/*
  @author: John spicer
  November 16, 2016
*/

import java.sql.*;

public class BoatRental {
   // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
   static final String DB_URL = "jdbc:mysql://localhost";

   //  Database credentials
   static final String USER = "root";
   //the user name; You can change it to your username (by default it is root).
   static final String PASS = "spicer";
   //the password; You can change it to your password (the one you used in MySQL server configuration).

   //Starts SQL Connection and runs SQL Queries
   public static void main(String[] args) {
     Connection conn = null;
     Statement stmt = null;
     try{
        //Register JDBC driver
        Class.forName("com.mysql.jdbc.Driver");

        //Open a connection to database
        System.out.println("Connecting to database...");
        conn = DriverManager.getConnection(DB_URL, USER, PASS);

        System.out.println("Creating database...");
        stmt = conn.createStatement();

        //Use SQL to Create Database;
        String sql = "CREATE DATABASE BoatRental";
        stmt.executeUpdate(sql);
        System.out.println("Database created successfully...");

        //Use SQL to select the database;
        sql = "use BoatRental";
        stmt.executeUpdate(sql);

        //Create Table Sailor
        sql = "create table Sailor( sid integer not null PRIMARY KEY, " +
            "sname varchar(20) not null," +
            "rating real not null," +
            "age integer not null)";
        stmt.executeUpdate(sql);

        //Create Table Boats
        sql = "create table Boats( bid integer not null PRIMARY KEY, bname varchar(40) not null, color varchar(40) not null)";
        stmt.executeUpdate(sql);

        //Create Table Reserves
        sql = "create table Reserves(sid integer not null, bid integer not null, day date not null," +
        "PRIMARY KEY(sid, bid, day), FOREIGN KEY (sid) REFERENCES Sailor(sid), FOREIGN KEY (bid) REFERENCES Boats(bid))";
        stmt.executeUpdate(sql);

        //Inserting Tuples for Sailor
        sql = "insert into Sailor values(22, 'Dustin', 7, 45)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(29, 'Brutus', 1, 33)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(31, 'Lubber', 8, 55)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(32, 'Andy', 8, 26)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(58, 'Rusty', 10, 35)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(64, 'Horatio', 7, 35)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(71, 'Zorba', 20, 18)";
        stmt.executeUpdate(sql);

        sql = "insert into Sailor values(74, 'Horatio', 9, 35)";
        stmt.executeUpdate(sql);

        //Inserting Tuples for Boats
        sql = "insert into Boats values(101, 'Interlake', 'Blue')";
        stmt.executeUpdate(sql);

        sql = "insert into Boats values(102, 'Interlake', 'Red')";
        stmt.executeUpdate(sql);

        sql = "insert into Boats values(103, 'Clipper', 'Green')";
        stmt.executeUpdate(sql);

        sql = "insert into Boats values(104, 'Marine', 'Red')";
        stmt.executeUpdate(sql);

        //Inserting Tuples for Reserves
        sql = "insert into Reserves values(22, 101, '2008-10-10')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(22, 102, '2008-10-10')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(22, 103, '2009-10-8')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(22, 104, '2009-10-9')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(31, 102, '2008-11-10')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(31, 103, '2008-11-6')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(31, 104, '2008-11-12')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(64, 101, '2008-9-5')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(64, 102, '2008-9-8')";
        stmt.executeUpdate(sql);

        sql = "insert into Reserves values(74, 103, '2008-9-8')";
        stmt.executeUpdate(sql);

        //Q1:  Find the sids of all sailors who have reserved red boats but not green boats
        Statement ques1 = conn.createStatement();
        ques1.executeQuery ("SELECT S.sname, S.sid FROM Sailor S, Boats B, Reserves R WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = 'red' AND S.sid NOT IN (SELECT S2.sid FROM Sailor S2, Boats B2, Reserves R2 WHERE S2.sid = R2.sid AND R2.bid = B2.bid AND B2.color = 'green')");
        ResultSet q1 = ques1.getResultSet();
        int count = 0;
        System.out.println("Q1:\n");
        while (q1.next())
        {
          System.out.println("Sailor name: " + q1.getString("sname") + " \n sid: " + q1.getString("sid"));
          ++count;
        }
        q1.close();
        ques1.close();
        System.out.println(count + " rows were retrieved"  + "\n");

        //Q2:  Find the names of sailors who have NOT reserved a red boat
        Statement ques2 = conn.createStatement();
        ques2.executeQuery("SELECT S.sname, S.sid FROM Sailor S WHERE S.sid NOT IN (SELECT R.sid FROM Reserves R WHERE R.bid IN (SELECT B.bid FROM Boats B WHERE B.color = 'red'))");
        ResultSet q2 = ques2.getResultSet();
        count = 0;
        System.out.println("Q2:\n");
        while (q2.next())
        {
          System.out.println("Sailor name: " + q2.getString("sname") + " \n sid: " + q2.getString("sid"));
          count++;
        }
        q2.close();
        ques2.close();
        System.out.println(count + " rows were retrieved"  + "\n");

        //Q3:  Find sailors whose rating is better than every sailor named Horatio.
        Statement ques3 = conn.createStatement();
        ques3.executeQuery("SELECT S.sname, S.sid FROM Sailor S WHERE S.rating > ALL(SELECT S2.rating FROM Sailor S2 WHERE S2.sname = 'Horatio')");
        ResultSet q3 = ques3.getResultSet();
        count = 0;
        System.out.println("Q3:\n");
        while (q3.next())
        {
          System.out.println("Sailor name: " + q3.getString("sname") + " \n sid: " + q3.getString("sid"));
          count++;
        }
        q3.close();
        ques3.close();
        System.out.println(count + " rows were retrieved"  + "\n");

        //Q4:  Find the names of sailors who have reserved all boats.
        Statement ques4 = conn.createStatement();
        ques4.executeQuery("SELECT s.sname, s.sid FROM Sailor s WHERE NOT EXISTS (SELECT b.bid FROM Boats b WHERE NOT EXISTS(SELECT r.bid FROM RESERVES r WHERE r.bid = b.bid AND r.sid = s.sid))");
        ResultSet q4 = ques4.getResultSet();
        count = 0;
        System.out.println("Q4:\n");
        while (q4.next())
        {
          System.out.println("Sailor name: " + q4.getString("sname") + " \n sid: " + q4.getString("sid"));
          count++;
        }
        q4.close();
        ques4.close();
        System.out.println(count + " rows were retrieved"  + "\n");

        //      Q5:  For each red boat, find its number of reservations.
        Statement ques5 = conn.createStatement();
        ques5.executeQuery("SELECT b.bid, COUNT(*) AS scount FROM Boats b, Reserves R WHERE r.bid = b.bid AND b.color = 'Red' GROUP BY b.bid");
        ResultSet q5 = ques5.getResultSet();
        count = 0;
        System.out.println("Q5:\n");
        while (q5.next())
        {
          System.out.println("Boat bid: " + q5.getString("bid") + " \n number of reservations: " + q5.getString("scount"));
          count++;
        }
        q5.close();
        ques5.close();
        System.out.println(count + " rows were retrieved"  + "\n");

        /*Drop Schema when done
        stmt = conn.createStatement();
				String query = "DROP DATABASE BoatRental";
				stmt.executeUpdate(query);
				System.out.println("DATABASE deleted successfully...");
        */

      }catch(SQLException se){
      //Handle errors for JDBC
      se.printStackTrace();
   }catch(Exception e){
      //Handle errors for Class.forName
      e.printStackTrace();
   }finally{
      //finally block used to close resources
      try{
         if(stmt!=null)
            stmt.close();
      }catch(SQLException se2){
      }// nothing we can do
      try{
         if(conn!=null)
            conn.close();
      }catch(SQLException se){
         se.printStackTrace();
      }//end finally try
   }//end try
   System.out.println("Goodbye!");
}//end main
}//end JDBCExample
