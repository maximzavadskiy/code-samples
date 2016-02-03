using UnityEngine;
using System.Collections;

public class DisablePlayerOnDeath : IOnDeath {
	
	public override void Die() {
		Camera.main.transform.parent = null;
		Camera.main.GetComponent<MouseLook>().enabled = false;
		
		gameObject.SetActive(false);
	}
}
