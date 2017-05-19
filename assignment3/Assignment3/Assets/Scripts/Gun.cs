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
        //lastShot = Time.deltaTime;
        //if ((lastShot - Time.deltaTime) < reloadSpeed)
        //{
        //    return;
        //}

        firing = true;
        GameObject newBullet = Instantiate(bulletMesh);
        newBullet.transform.position = transform.position;
        newBullet.transform.rotation = transform.rotation;
        newBullet.transform.Rotate(new Vector3(0, 0, -90));
        newBullet.transform.Translate(new Vector3(20, 30, 0));
        newBullet.transform.localScale = new Vector3(0.05f,0.05f,0.05f);
        bulletBuffer.Add(newBullet);
        
        --numberOfBullets;
        
    }

    void Update()
    {
        if(!picked)
            transform.Rotate(new Vector3(0, 0, 30) * Time.deltaTime);
        if (firing)
        {
            foreach(GameObject bullet in bulletBuffer)
            {
               // bullet.transform.Translate(new Vector3(0, -100, 0) * Time.deltaTime);
            }
        }
    }
}
