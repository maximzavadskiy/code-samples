using UnityEngine;
using System.Collections;

public class HealthHUD : MonoBehaviour {
	
	Health playerHealth;
	
	void Start() {
		playerHealth = GameObject.FindGameObjectWithTag("Player").GetComponent<Health>();	
	}
	
	void Update () {
		if(playerHealth) GetComponent<GUIText>().text = playerHealth.currentHealth.ToString();
	}
}
