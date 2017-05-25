using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    public float bulletSpeed;
    public float massFactor;
    public float maxBulletTime;
    public int bulletDamage;
    private bool collided;

    void Start()
    {
        collided = false;
        Destroy(gameObject, maxBulletTime);
    }

    void Update()
    {
        if (!collided)
        {
            transform.Translate(new Vector3(0, -bulletSpeed, 0) * Time.deltaTime);
            //hardcoded but better for collision detection
            transform.Translate(new Vector3(0, -massFactor, 0) * Time.deltaTime, Space.World);
        }

    }

    void OnTriggerEnter(Collider col)
    {
        collided = true;
        this.GetComponent<ParticleSystem>().Play();
        if(col.gameObject.GetComponent<Player>())
        {
            col.gameObject.GetComponent<Player>().injure(this.bulletDamage);
        }
        if (col.gameObject.GetComponent<Enemy>())
        {
           // col.gameObject.GetComponent<Enemy>().injure(this.bulletDamage);
        }
    } 
}
