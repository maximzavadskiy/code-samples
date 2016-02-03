using UnityEngine;
using System.Collections;

public class Bullet : MonoBehaviour {
	
	public float speed = 1f;
	//destroy bullet after some time, so it does not flood resources
	public float lifetime = 50; 		
	public int damage = 1;
	
	public GameObject explosiveEffectPrefub;

	void OnEnable () {

		Invoke("Destroy", lifetime);
		rigidbody.velocity = transform.forward*speed;
	}
	
	void OnTriggerEnter(Collider col) {
		GameObject.Instantiate(explosiveEffectPrefub, transform.position, Quaternion.identity);
		col.SendMessage("ApplyDamage", damage, SendMessageOptions.DontRequireReceiver);
		Destroy();
	}
	
	void Destroy() {
		GameObject.Destroy(gameObject);
	}
}
