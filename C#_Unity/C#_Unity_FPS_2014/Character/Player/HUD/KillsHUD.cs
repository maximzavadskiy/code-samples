using UnityEngine;
using System.Collections;

public class KillsHUD : MonoBehaviour {
	
	int kills = 0;
	
	void Start() {
		GetComponent<GUIText>().text = "0";
		//subscribe to death events
		Events.instance.OnDeath += UpdateKills; 
	}
	
	void UpdateKills (GameObject deadEntity) {
		if(deadEntity.CompareTag("Enemy")) {
			kills++;
			GetComponent<GUIText>().text = kills.ToString(); 
		}
	}
}
