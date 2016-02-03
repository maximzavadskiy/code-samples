using UnityEngine;
using System.Collections;

//common launch procedure, used by NPC and Player.
public class BulletLauncher: MonoBehaviour{
	
	// how far from the player should we launch the bullet, so it does not blink screen 
	public float bulletLaunchOffsetDistance = 1.5f; 	
	public float shotPeriod = 1f;
	
	float lastShotTime = 0f;
	//shoots a bullet if shotPeriod is passed since last shot
	public void TryLaunchBullet(GameObject prefub, Vector3 position, Vector3 direction) {
		if(Time.time > lastShotTime + shotPeriod) {
			lastShotTime = Time.time;
			GameObject bullet = (GameObject) GameObject.Instantiate(prefub, position + direction.normalized*bulletLaunchOffsetDistance, Quaternion.LookRotation(direction));
			//ignore collision, so bullet will go out from the shooter
			Physics.IgnoreCollision(bullet.collider, collider);
		}
	}
}
