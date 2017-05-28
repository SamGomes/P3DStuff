using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum GunType {
    Pistol, MachineGun, Bazooka, Laser
}

public class Gun : Pickable {

    public AudioClip gunSound;
    public AudioClip emptyGunSound;
    public GameObject bulletMesh;
    public float firingDelay;
    private int numberOfBullets;
    public int numberOfPickupBullets;
    public int maxNumberOfBullets;
    public GunType gunType;
    public bool isABulletsWeapon;
    

    private float lastShot;

    public int getNumberOfBullets()
    {
        return numberOfBullets;
    }

    void Start()
    {
        if (isABulletsWeapon)
        {
            addBullets(numberOfPickupBullets);
        }
    }

    public void addBullets(int numberOfBullets)
    {
        int aux = this.numberOfBullets + numberOfBullets;
        this.numberOfBullets = aux > maxNumberOfBullets ? maxNumberOfBullets : aux;
    }

    public void fire()
    {
        fire(null);
    }

    public void fire(Collider ignorable)
    {
        if (this.isABulletsWeapon) //non-bullet weapons like a laser dont have bullets to fire
        {
            if (numberOfPickupBullets > numberOfBullets)
            {
                numberOfPickupBullets = numberOfBullets;
            }
            if (this.numberOfBullets == 0 || (Time.realtimeSinceStartup - lastShot) < firingDelay)
            {
                if (this.numberOfBullets == 0)
                {
                    if (this.GetComponent<AudioSource>())
                    {
                        GetComponent<AudioSource>().clip = emptyGunSound;
                        if ((Time.realtimeSinceStartup - lastShot) >= firingDelay)
                        {
                            GetComponent<AudioSource>().Play();
                            lastShot = Time.realtimeSinceStartup;
                        }
                    }
                }
                return;
            }
            if (this.GetComponent<AudioSource>())
            {
                GetComponent<AudioSource>().clip = gunSound;
                GetComponent<AudioSource>().Play();
            }

            if (this.GetComponent<ParticleSystem>())
            {
                this.GetComponent<ParticleSystem>().Play();
            }
            lastShot = Time.realtimeSinceStartup;
            GameObject newBullet = Instantiate(bulletMesh);

            newBullet.transform.position = transform.position;
            newBullet.transform.rotation = transform.rotation;
            newBullet.transform.Rotate(new Vector3(0, 0, -90));
            newBullet.GetComponent<Bullet>().gunType = this.gunType;
            newBullet.GetComponent<Bullet>().ignorable = ignorable;


            --numberOfBullets;
        }

    }
}
