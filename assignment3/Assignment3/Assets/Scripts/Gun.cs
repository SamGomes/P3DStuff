using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gun : MonoBehaviour {

    public GameObject bulletMesh;
    public float reloadSpeed;
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
        if (this.numberOfBullets == 0 || (Time.realtimeSinceStartup - lastShot) < reloadSpeed)
        {
            return;
        }
        GetComponent<AudioSource>().Play();
        lastShot = Time.realtimeSinceStartup;
        GameObject newBullet = Instantiate(bulletMesh);
        newBullet.transform.position = transform.position;
        newBullet.transform.rotation = transform.rotation;
        newBullet.transform.Rotate(new Vector3(0, 0, -90));
        newBullet.transform.Translate(new Vector3(8, -25, 12));
        newBullet.transform.localScale = new Vector3(0.05f,0.05f,0.05f);
        bulletBuffer.Add(newBullet);
        
        --numberOfBullets;
        
    }

    void Update()
    {
        if(!picked)
            transform.Rotate(new Vector3(0, 0, 30) * Time.deltaTime);
        
    }
}
