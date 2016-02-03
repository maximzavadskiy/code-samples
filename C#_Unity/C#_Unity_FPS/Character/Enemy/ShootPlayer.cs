using UnityEngine;
using System.Collections;

public class ShootPlayer : MonoBehaviour {
	
	public GameObject bulletPrefub;
	
	GameObject player;
	
	void Start () {
		player = GameObject.FindGameObjectWithTag("Player");
	}
	
	
	void Update () {
		if(player) {
			//check if faces the player
			if(Physics.Raycast(transform.position,  player.transform.position - transform.position, 1 << LayerMask.NameToLayer("Player"))) {
				
				Vector3 aimVector = GetComponent<IAimCalculator>().CalculateAim(transform.position, player.transform.position, bulletPrefub.GetComponent<Bullet>().speed);
				
				RaycastHit hit = new RaycastHit();
				Physics.Raycast(transform.position, aimVector, out hit);
				//make sure tht bullet won't hit enemies, check agains aim vector, as projectiles can be thrown over enemies!
				if( hit.transform == null || ! hit.transform.CompareTag("Enemy")) {
				
					GetComponent<BulletLauncher>().TryLaunchBullet(
					bulletPrefub, 
					transform.position, 
					aimVector);
				}
			}
		}
	}
}
