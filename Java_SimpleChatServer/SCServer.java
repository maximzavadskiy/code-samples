/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author maxim
 */

package simplechatserver;

import java.net.*;
import java.io.*;
import java.util.ArrayList;


public class SCServer
{
  public static void main(String[] args)  throws Exception
  {
    SCServer TheServer=new SCServer(4444);
    TheServer.run();
  }

  SCSUsers registered_users;

  int port;
  ServerSocket server_socket;

  ArrayList<SCSUserConnection> user_connections=new ArrayList<SCSUserConnection>();

  public SCServer(int port_no)
  {
    port=port_no;
    registered_users=new SCSUsers();
  }

  public void run() throws Exception
  {
    try
    {
      server_socket = new ServerSocket(port);
      new SCSUsersDAO();
    }
    catch (IOException e)
    {
      System.out.println("Exception while creating the server: "+e.getMessage());
      throw e;
    }

    while (true)
    {
      Socket clientSocket = null;
      try
      {
        clientSocket = server_socket.accept();
      }
      catch (IOException e)
      {
        System.out.println("Exception while accepting the client: "+e.getMessage());
        continue;
      }

      System.out.println("New client connected!!");

      SCSUserConnection user_connection=new SCSUserConnection(clientSocket,this);
      user_connections.add(user_connection);
      user_connection.run_communicate();
    }
  }

  boolean usernameAllowed(String requested_username, SCSUserConnection client)
  {
    String[] users=getConnectedUsers();
    for(String conn_user:users)
    {
      if(conn_user.equals(requested_username)) return false;
    }

    //return true;
    try
    {
      registered_users.loadUsers();//updating info about registered users
      if(registered_users.containsUsername(requested_username)) return true;
      else return false;
    }
    catch(Exception e)
    {
      client.onError(e);
    }
    
    return false;
  }
         
  void notifyNewMessage(String sender, String message)
  {
    for(SCSUserConnection connection: user_connections)
    {
      connection.onNewMessage(sender,message);
    }
  }

  void notifyUserAvailable(String username)
  {
    for(SCSUserConnection connection: user_connections)
    {
      connection.onUserAvailable(username);
    }
  }

  void notifyUserOffline(String username)
  {
    for(SCSUserConnection connection: user_connections)
    {
      connection.onUserOffline(username);
    }
  }

  String[] getConnectedUsers()
  {
    String[] usernames= new String[user_connections.size()];
    for(int i=0;i<usernames.length;i++)
    {
      usernames[i]=user_connections.get(i).getUsername();
    }
    return usernames;
  }

  void closeUserConnection(SCSUserConnection aThis)
  {
    user_connections.remove(aThis);
  }
}
