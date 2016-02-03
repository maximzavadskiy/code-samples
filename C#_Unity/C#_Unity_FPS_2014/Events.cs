using UnityEngine;
using System.Collections;

//small event system for anonymous messaging (senders do not need to know about receivers)
public class Events : MonoBehaviour {
	
	public delegate void DeathAction(GameObject who);
    public event DeathAction OnDeath;
	
	public static Events instance;
	
	//ensure that Events are cleared each new level
	public void Awake() {
		instance = this;
	}
	
	public void FireOnDeath(GameObject deadEntity) {
		if(OnDeath != null) 
			OnDeath(deadEntity);
	}
}
