using UnityEngine;
using System.Collections;

// handles game over situation
public class GameOver : MonoBehaviour {

	public GUIText gameOverText;
	
	
	void Start () {
		Time.timeScale = 1; //set time scale back to 1
		Events.instance.OnDeath += CheckPlayerDead;
	}
	
	void CheckPlayerDead(GameObject deadEntity) {
		if(deadEntity.CompareTag("Player")) {
			gameOverText.enabled = true;
			Time.timeScale = 0;
		}
	}
}
