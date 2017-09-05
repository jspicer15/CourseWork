import java.sql.*;

public class example {
   // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
   static final String DB_URL = "jdbc:mysql://localhost";

   //  Database credentials
   static final String USER = "root";
   //the user name; You can change it to your username (by default it is root).
   static final String PASS = "spicer";
   //the password; You can change it to your password (the one you used in MySQL server configuration).

   public static void main(String[] args) {
   Connection conn = null;
   Statement stmt = null;
   try{
      //STEP 1: Register JDBC driver
      Class.forName("com.mysql.jdbc.Driver");

      //STEP 2: Open a connection to database
      System.out.println("Connecting to database...");
      conn = DriverManager.getConnection(DB_URL, USER, PASS);

      System.out.println("Creating database...");
      stmt = conn.createStatement();

      //STEP 3: Use SQL to Create Database;
      String sql = "CREATE DATABASE VehicleOffice";
      stmt.executeUpdate(sql);
      System.out.println("Database created successfully...");

      //STEP 4: Use SQL to select the database;
      sql = "use VehicleOffice";
      stmt.executeUpdate(sql);

     //STEP 5: Use SQL to create Tables;
     //STEP 5.1: Create Table Branch;
      sql = "create table branch( branch_id integer not null PRIMARY KEY, " +
          "branch_name varchar(20) not null," +
          "branch_addr varchar(50)," +
          "branch_city varchar(20) not null," +
          "branch_phone integer)";
      stmt.executeUpdate(sql);

      //STEP 5.2: Create Table Driver;
      sql = "create table driver(driver_ssn integer not null PRIMARY KEY," +
          "driver_name varchar(20) not null," +
          "driver_addr varchar(50) not null," +
          "driver_city varchar(20) not null," +
          "driver_birthdate date not null," +
          "driver_phone integer)";
      stmt.executeUpdate(sql);

     //STEP 5.3: Create Table License;
     //Your Task 1!
      sql = "create table license(license_no integer not null PRIMARY KEY," +
            "driver_ssn integer not null," +
            "license_type char(1) not null," +
            "license_class integer not null," +
            "license_expiry date not null," +
            "issue_date date not null," +
            "branch_id integer not null," +
            "FOREIGN KEY(driver_ssn) references driver(driver_ssn)," +
            "FOREIGN KEY(branch_id) references branch(branch_id))";
      stmt.executeUpdate(sql);

      //STEP 5.4: Create Table Exam;
      //Your Task 2!
      sql = "create table exam(driver_ssn integer not null," +
            "branch_id integer not null," +
            "exam_date date not null," +
            "exam_type char(1) not null," +
            "exam_score integer not null," +
            "PRIMARY KEY(driver_ssn, branch_id, exam_date)," +
            "FOREIGN KEY(driver_ssn) references driver(driver_ssn)," +
            "FOREIGN KEY(branch_id) references branch(branch_id))";;
      stmt.executeUpdate(sql);


       //STEP 6: Use SQL to insert tuples into tables;
       //STEP 6.1: insert tuples into Table Branch;
        sql = "insert into branch values(10, 'Main', '1234 Main St.', 'Vancouver', 5551234)";
        stmt.executeUpdate(sql);

        sql = "insert into branch values(20, 'Richmond', '23 No.3 Road', 'Richmond', 5552331)";
        stmt.executeUpdate(sql);

        //Your Task 3: insert the rest of tuples in Table Branch;
        sql = "insert into branch values(30, 'West Creek', '251 Creek Rd.', 'Sechelt', 5552511)";
        stmt.executeUpdate(sql);

        sql = "insert into branch values(40, 'Blenheim', '1342 W.22 Ave.', 'Burnaby', 5551342)";
        stmt.executeUpdate(sql);
       //STEP 6.2: insert tuples into Table driver;
        sql = "insert into driver values(11111111, 'Bob Smith', '111 E. 11 St.', 'Vancouver', '1975-01-01', 5551111)";
        stmt.executeUpdate(sql);

        sql = "insert into driver values(22222222, 'John Walters', '222 E. 22 St.', 'Burnaby', '1976-02-02', 5552222)";
        stmt.executeUpdate(sql);

      //Your Task 4: insert the rest of tuples in Table Driver;
        sql = "insert into driver values(33333333, 'Troy Rops', '333 W.33 Ave', 'Richmond', '1970-03-03', 5553333)";
        stmt.executeUpdate(sql);

        sql = "insert into driver values(44444444, 'Kevin Mark', '444 E. 44 St.', 'Vancouver', '1974-04-04', 5554444)";
        stmt.executeUpdate(sql);
      //STEP 6.3: insert tuples into Table license;
      //Your Task 5: insert all tuples into Table license;
        sql = "insert into license values(1, 11111111, 'D', 5 , '1999-05-25', '1997-05-25', 20)";
        stmt.executeUpdate(sql);

        sql = "insert into license values(2, 22222222, 'D', 5 , '1998-08-29', '1996-08-29', 40)";
        stmt.executeUpdate(sql);

        sql = "insert into license values(3, 33333333, 'L', 5 , '1997-12-27', '1997-06-27', 20)";
        stmt.executeUpdate(sql);

        sql = "insert into license values(4, 44444444, 'D', 5 , '1999-08-30', '1997-08-30', 40)";
        stmt.executeUpdate(sql);
      //STEP 6.4: insert all tuples into Table exam;
      //Your Task 6: insert all tuples into Table exam;
        sql = "insert into exam values(11111111, 20, '1997-05-25', 'D', 79)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(11111111, 20, '1997-12-02', 'L', 97)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(22222222, 30, '1996-05-06', 'L', 25)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(22222222, 40, '1996-06-10', 'L', 51)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(22222222, 40, '1996-08-29', 'D', 81)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(33333333, 10, '1997-07-07', 'L', 45)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(33333333, 20, '1997-06-27', 'L', 49)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(33333333, 20, '1997-07-27', 'L', 61)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(44444444, 10, '1997-07-27', 'L', 71)";
        stmt.executeUpdate(sql);

        sql = "insert into exam values(44444444, 20, '1997-08-30', 'D', 65)";
        stmt.executeUpdate(sql);

        //STEP 7: Use SQL to ask queries and retrieve data from the tables;
        //An example to retrieve branch ID, name, address from Table Branch, and display these values;
        Statement s = conn.createStatement ();
        s.executeQuery ("SELECT branch_id, branch_name, branch_addr FROM branch");
        ResultSet rs = s.getResultSet ();
        int count = 0;
        while (rs.next ())
        {
            int idVal = rs.getInt ("branch_id");
            String nameVal = rs.getString ("branch_name");
            String addrVal = rs.getString ("branch_addr");
            System.out.println (
                    "branch id = " + idVal
                    + ", name = " + nameVal
                    + ", address = " + addrVal);
            ++count;
        }
        rs.close ();
        s.close ();
        System.out.println (count + " rows were retrieved");

        //Your Task 7: Write SQL for Q1, Q2 and Q3 in Lab instruction and display the answers.
        Statement ques1 = conn.createStatement();
        ques1.executeQuery ("SELECT driver_name FROM driver d, branch b, license l WHERE D.driver_ssn = L.driver_ssn AND L.branch_id = B.branch_id AND branch_name = 'Richmond'");
        ResultSet q1 = ques1.getResultSet();
        count = 0;
        while (q1.next())
        {
          System.out.println("driver_name: " + q1.getString("driver_name"));
          ++count;
        }
        q1.close();
        ques1.close();
        System.out.println(count + " rows were retrived");

        Statement ques2 = conn.createStatement();
        ques2.executeQuery("SELECT DISTINCT driver_name, count(branch_id) FROM exam e, driver d WHERE e.driver_ssn = d.driver_ssn GROUP BY e.branch_id HAVING COUNT(e.branch_id) > 1");
        ResultSet q2 = ques2.getResultSet();
        count = 0;
        while (q2.next())
        {
          System.out.println("driver_name: " + q2.getString("driver_name"));
          ++count;
        }
        q2.close();
        ques2.close();
        System.out.println(count + " rows were retrived");

        Statement ques3 = conn.createStatement();
        ques3.executeQuery("SELECT DISTINCT driver_name FROM driver WHERE driver_name NOT IN (SELECT driver_name FROM exam AS a JOIN exam AS b ON a.driver_ssn = b.driver_ssn AND a.exam_date > b.exam_date AND a.exam_score > b.exam_score, driver d WHERE a.driver_ssn = d.driver_ssn)");
        ResultSet q3 = ques3.getResultSet();
        count = 0;
        while (q3.next())
        {
          System.out.println("driver_name: " + q3.getString("driver_name"));
          ++count;
        }
        q3.close();
        ques3.close();
        System.out.println(count + " rows were retrieved");

        //Q1
        //String query1 = "select driver_name from driver, license, branch";

        //ResultSet
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
