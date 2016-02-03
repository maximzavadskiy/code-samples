package simplechatserver;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author maxim
 */


public class SCProtocolParser
{
  public enum SCMessageType
  {
    USERNAME_REQUEST,//request of nick from server, syntax: USERNAME_REQUEST
    USERNAME_REPLY,//reply with nick from client,syntax: USERNAME_REQUEST [username]
    WRONG_USERNAME,//used to show that nickname in USERNAME_REPLY is incorrect and the client should send another USERNAME_REPLY after this message, syntax: WRONG_USERNAME
    USERNAME_ACCEPTED,//the server sends a message that it accepts a username, now client can send  PUSH_MESSAGE and LOGOUT messages, syntax: USERNAME_ACCEPTED
    NEW_MESSAGE,//server notifies a client about a new message, syntax: NEW_MESSAGE [user] [message]
    PUSH_MESSAGE,//client sends a new chat message to other users, syntax: PUSH_MESSAGE [message]
    USER_AVAILABLE, USER_OFFLINE,//server notifies about logged in/out users, syntax: USER_AVAILABLE [username], syntax:  USER_OFFLINE [username]
    LOGOUT,//client notifies the server about logging our,syntax: LOGOUT
    /**An error message that reports unrecoverable exception.
     *E.g. Used to identify a wrong message with unrecognizable type or a message that is not expected*/
    ERROR;// a message used to send an error message to a client, server drops the connection after that, syntax: ERROR [error message]

    /*public String getStringEquivalent()
    {
      if(this==USERNAME_REQUEST) return "USERNAME_REQUEST";
      if(this==USERNAME_REPLY) return "USERNAME_REPLY";
      if(this==WRONG_USERNAME) return "WRONG_USERNAME";
      if(this==NEW_MESSAGE) return "NEW_MESSAGE";
      if(this==PUSH_MESSAGE) return "PUSH_MESSAGE";
      if(this==USER_AVAILABLE) return "USER_AVAILABLE";
      if(this==USER_OFFLINE) return "USER_OFFLINE";
      if(this==LOGOUT) return "LOGOUT";
      return "";
    }*/

    /*static public SCMessageType getType(String type)
    {
      if(type.equals("USERNAME_REQUEST")) return USERNAME_REQUEST;
      if(type.equals("USERNAME_REPLY")) return USERNAME_REPLY;
      if(type.equals("WRONG_USERNAME")) return WRONG_USERNAME;
      if(type.equals("NEW_MESSAGE")) return NEW_MESSAGE;
      if(type.equals("PUSH_MESSAGE")) return PUSH_MESSAGE;
      if(type.equals("USER_AVAILABLE")) return USER_AVAILABLE;
      if(type.equals("USER_OFFLINE")) return USER_OFFLINE;
      if(type.equals("LOGOUT")) return LOGOUT;
      return WRONG_MESSAGE;
    }*/
  }

  public static SCMessageType getMessageType(String message ) throws IllegalArgumentException
  {
    String stype=message.split(" ")[0];
    return SCMessageType.valueOf(stype);
  }

  public static String makeUsername_request()
  {
    return SCMessageType.USERNAME_REQUEST.toString();
  }

  public static String makeUsername_reply(String username)
  {
    return SCMessageType.USERNAME_REPLY.toString()+" "+username;
  }
  public static String parseUsername_reply(String message) throws WrongMessageSyntax
  {
    if(message.split(" ").length>2) throw new WrongMessageSyntax();
    return message.split(" ")[1];
  }

  public static String makeUsername_accepted()
  {
    return SCMessageType.USERNAME_ACCEPTED.toString();
  }

  public static String makeWrong_username()
  {
    return SCMessageType.WRONG_USERNAME.toString();
  }

  public static String makeNew_message(String sender, String message)
  {
    return SCMessageType.NEW_MESSAGE.toString()+" "+sender+" "+message;
  }
  /**parses a sender from a NEW_MESSAGE message*/
  public static String parseNew_messageSender(String message)
  {
    return message.split(" ")[1];
  }
  /**parses a chat Message from a NEW_MESSAGE message*/
  public static String parseNew_messageMessage(String message)
  {
    return message.split(" ",3)[2];
  }

  public static String makePush_message(String message)
  {
    return SCMessageType.PUSH_MESSAGE.toString()+" "+message;
  }
  public static String parsePush_message(String message)
  {
    return message.split(" ",2)[1];
  }

  public static String makeUser_available(String username)
  {
    return SCMessageType.USER_AVAILABLE.toString()+" "+username;
  }
  public static String parseUser_available(String message)
  {
    return message.split(" ")[1];
  }

  public static String makeUser_offline(String username)
  {
    return SCMessageType.USER_OFFLINE.toString()+" "+username;
  }
  public static String parseUser_offline(String message)
  {
    return message.split(" ")[1];
  }

  public static String makeLogout()
  {
    return SCMessageType.LOGOUT.toString();
  }

  public static String makeError(String info)
  {
    return SCMessageType.ERROR.toString()+" "+info;
  }

  public static String parseError(String message)
  {
    return message.split(" ",2)[1];
  }
}
