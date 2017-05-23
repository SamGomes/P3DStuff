using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    public float bulletSpeed;
    public float maxBulletTime;
    private bool collided;

    void Start()
    {
        collided = false;
       // Destroy(gameObject, maxBulletTime);
    }

    void Update()
    {
        if(!collided)
            transform.Translate(new Vector3(0, -bulletSpeed, 0) * Time.deltaTime);   
    }

    void OnTriggerEnter()
    {
        collided = true;
        this.GetComponent<ParticleSystem>().Play();
        this.GetComponent<MeshRenderer>().gameObject.SetActive(false);
    } 
}
