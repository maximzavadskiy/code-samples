/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author maxim
 */

package simplechatserver;

import java.util.ArrayList;

public class SCSUsers
{
  ArrayList<String> usernames;

  public SCSUsers()
  {
    usernames=new ArrayList<String>();
  }

  public void loadUsers() throws Exception
  {
    usernames=SCSUsersDAO.getInstance().getUsernames();
  }

  public boolean containsUsername(String username)
  {
    return usernames.contains(username);
  }
}
