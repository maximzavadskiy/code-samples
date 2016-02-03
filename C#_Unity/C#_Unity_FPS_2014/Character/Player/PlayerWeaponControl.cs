using UnityEngine;
using System.Collections;

[RequireComponent(typeof(BulletLauncher))]

public class PlayerWeaponControl : MonoBehaviour {
	
	public GameObject bullet1;
	public GameObject bullet2;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetButton("Fire1")) {
			TryLaunchBullet(bullet1); 
		}
		
		if(Input.GetButton("Fire2")) {
			TryLaunchBullet(bullet2); 	
		}
	}
	//launch bullet if enough time passed since last launch
	void TryLaunchBullet(GameObject bulletPrefab) {
			GetComponent<BulletLauncher>().TryLaunchBullet(bulletPrefab, Camera.main.transform.position,Camera.main.transform.forward);
	}
}
