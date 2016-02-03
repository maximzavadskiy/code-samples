/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author maxim
 */

package simplechatserver;

import simplechatserver.SCProtocolParser.SCMessageType;
import static simplechatserver.SCProtocolParser.SCMessageType.*;
import java.net.*;
import java.io.*;

public class SCSUserConnection extends Thread
{
  private String username="";

  private Socket socket;
  private SCServer server;

  private PrintWriter out;
  private BufferedReader in;

  public SCSUserConnection(Socket client_socket, SCServer serv)
  {
    socket=client_socket;
    server=serv;
  }

  public void run_communicate()
  {
    start();
  }

  public void run()
  {
    try
    {
      out = new PrintWriter(socket.getOutputStream(), true);
      in = new BufferedReader( new InputStreamReader(socket.getInputStream()) );
      requestUsername();
      System.out.println("User "+username+" has logged in.");
      server.notifyUserAvailable(username);

      String[] users=server.getConnectedUsers();
      for(String name: users)
      {
        if(name!=username) notifyUserAvailable(name);
      }

      SCMessageType mes_type=LOGOUT;
      do
      {
        System.out.println("begin Do");
        String client_message=in.readLine();
       System.out.println("New message from client "+ username+": "+client_message);
        mes_type=SCProtocolParser.getMessageType(client_message);
        if(mes_type==PUSH_MESSAGE)
        {
          server.notifyNewMessage(username, SCProtocolParser.parsePush_message(client_message));
        }
        else if(mes_type!=LOGOUT)
        {
          throw new Exception("Unexpected type of a message: "
                  +SCProtocolParser.getMessageType(client_message)+" was expected PUSH_MESSAGE or LOGOUT");
        }
      }while(mes_type!=LOGOUT);
      close();
      System.out.println("Connection with user "+username+" ended successfully");
    }
    catch(Exception e)
    {
      onError(e);
    }
  }

  public String getUsername()
  {
    return username;
  }
  
  private void requestUsername() throws Exception
  {
    try
    {
      System.out.println("Requesting username...");
      out.println(SCProtocolParser.makeUsername_request());

      while(true)
      {
        try
        {
          String client_reply=in.readLine();
          System.out.println("Client reply: "+client_reply);
          if(SCProtocolParser.getMessageType(client_reply)==USERNAME_REPLY)
          {
            String requested_username=SCProtocolParser.parseUsername_reply(client_reply);
            if(server.usernameAllowed(requested_username,this))
            {
              out.println(SCProtocolParser.makeUsername_accepted());
              username=requested_username;
              break;
            }
            else
            {
              out.println(SCProtocolParser.makeWrong_username());
              continue;
            }
            
          }
          else throw new Exception("Unexpected type of a message: "+SCProtocolParser.getMessageType(client_reply)+" was expected USERNAMEREPLY");
        }catch(WrongMessageSyntax e)
        {
          out.println(SCProtocolParser.makeWrong_username());
          continue;
        }
      }

    } catch(IllegalArgumentException ex)
    {
      throw new Exception("Unknown type of a message");
    }
  }

  void close() throws Exception
  {
      System.out.println("User "+username+" has logged out.");
      server.notifyUserOffline(username);

      server.closeUserConnection(this);
      out.close();
      in.close();
      socket.close();
  }

  void onUserAvailable(String _username)
  {
    notifyUserAvailable(_username);
  }

  void onUserOffline(String _username)
  {
    notifyUserOffline(_username);
  }

  void onNewMessage(String sender, String message)
  {
    out.println(SCProtocolParser.makeNew_message(sender, message));
  }

  void onError(Exception e)
  {
     System.out.println("Exception while communicating with the client: "+e.getMessage());
     e.printStackTrace();
     out.println(SCProtocolParser.makeError(e.getMessage()));
     try{ close(); }catch(Exception close_e){}
  }

  private void notifyUserAvailable(String name)
  {
    out.println(SCProtocolParser.makeUser_available(name));
  }

  private void notifyUserOffline(String name)
  {
    out.println(SCProtocolParser.makeUser_offline(name));
  }

}
