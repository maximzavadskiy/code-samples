/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author maxim
 */

package simplechatserver;

import java.sql.*;
import java.util.ArrayList;

public class SCSUsersDAO
{
    static String db_url="jdbc:mysql://mysql.db4free.net/maximzavadskiy";
    static String db_username="maximzavadskiy";
    static String db_password="nkdfnuhbg";

    private static SCSUsersDAO instance;
    Connection connect;


    public static SCSUsersDAO getInstance() throws Exception
    {
      if(instance==null) instance=new SCSUsersDAO();
      return instance;
    }

    protected SCSUsersDAO() throws Exception
    {
      try
      {
           //a trick ;)
          String pass = new String();
          for(int i=0;i<db_password.length();i++)
          {
              pass+=(char)((int)db_password.charAt(i) +1) ;
          }
                
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            connect = DriverManager.getConnection(SCSUsersDAO.db_url, db_username, pass);
            if (!connect.isClosed()) {
                System.out.println("Successfully connected to MySQL server using TCP/IP...");
                Statement stmt= connect.createStatement();
            }      
      }
      catch(Exception e)
      {
        System.err.println("Exception while connecting to the database: " + e.getMessage());
        throw e;
      }
    }

    public ArrayList<String> getUsernames() throws Exception
    {
        ArrayList<String> usernames=new ArrayList<String>();
        try
        {
            Statement stmt = connect.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM nickname");
            while (rs.next())
            {
                String username=rs.getString("name");
                usernames.add(username);
            }
        }
        catch (Exception ex)
        {
            System.err.println("Exception: " + ex.getMessage());
            throw ex;
        }
        return usernames;

    }
}
