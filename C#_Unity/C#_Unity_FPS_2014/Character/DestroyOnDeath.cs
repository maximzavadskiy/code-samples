using UnityEngine;
using System.Collections;

public class DestroyOnDeath : IOnDeath {
	
	public override void Die() {
		GameObject.Destroy(gameObject);	
	}
}
