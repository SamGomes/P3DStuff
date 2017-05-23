using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gun : MonoBehaviour {

    public GameObject bulletMesh;
    public float firingDelay;
    public float bulletDamage;
    public bool picked;
    public int numberOfBullets;

    private bool firing;
    private List<GameObject> bulletBuffer;

    private float lastShot;
    void Start()
    {
        this.picked = false;
        this.firing = false;

        bulletBuffer = new List<GameObject>();
    }

    public void fire()
    {
        if (this.numberOfBullets == 0 || (Time.realtimeSinceStartup - lastShot) < firingDelay)
        {
            return;
        }
        GetComponent<AudioSource>().Play();
        lastShot = Time.realtimeSinceStartup;
        GameObject newBullet = Instantiate(bulletMesh);
        newBullet.transform.position = transform.position + new Vector3(0.3f,0,0);
        newBullet.transform.rotation = transform.rotation;
        newBullet.transform.Rotate(new Vector3(0, 0, -90));
 
        bulletBuffer.Add(newBullet);
        
        --numberOfBullets;
        
    }

    void Update()
    {
        if(!picked)
            transform.Rotate(new Vector3(0, 0, 30) * Time.deltaTime);
    }
}
