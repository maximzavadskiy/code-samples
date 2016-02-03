using UnityEngine;
using System.Collections;

[RequireComponent(typeof(IOnDeath))]

public class Health : MonoBehaviour {
	
	public int maxHealth = 50;
	
	public int currentHealth;
	
	void Start() {
		currentHealth = maxHealth;
	}
	
	public void ApplyDamage(int damage) {
		currentHealth -= damage;
		if(currentHealth <= 0) {
			currentHealth = 0;
			
			GetComponent<IOnDeath>().Die();
			Events.instance.FireOnDeath(gameObject);
		}
	}
}
