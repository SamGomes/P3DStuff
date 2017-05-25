using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum GunType {
    Pistol, MachineGun, Bazooka
}

public class Gun : MonoBehaviour {

    public GameObject bulletMesh;
    public float firingDelay;
    public bool picked;
    private int numberOfBullets;
    public int maxNumberOfBullets;
    public GunType gunType;
    

    private bool firing;
    private List<GameObject> bulletBuffer;

    private float lastShot;

    public int getNumberOfBullets()
    {
        return numberOfBullets;
    }

    void Start()
    {
        addBullets(maxNumberOfBullets);
        this.firing = false;

        bulletBuffer = new List<GameObject>();
    }

    public void addBullets(int numberOfBullets)
    {
        int aux = this.numberOfBullets + numberOfBullets;
        this.numberOfBullets = aux > maxNumberOfBullets ? maxNumberOfBullets : aux;
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
        if (transform.parent.gameObject.name == "FPSController")
        {
            newBullet.transform.position = transform.position + new Vector3(0.3f, 0, 0);
        }
        else
        {
            newBullet.transform.position = transform.position + new Vector3(-6.0f, 3.0f, 0.0f);
        }
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
