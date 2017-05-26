using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public AudioClip hurtSound;
    public AudioClip deathSound;

    private ScoreController scoreController;

    public GameObject player;
    public float firingDelay;
    private float lastShot;
    public int life;
    private bool isDead = false;
    private GunType lastGunToShoot;
    private bool lastShotWasHeadShot;
    private int headShotMultiplayer = 4;
    public Collider headCollider;

    public void injure(int hp, GunType gun, Collider collider)
    {
        if (collider == headCollider)
        {

            life -= 4 * hp;
            lastShotWasHeadShot = true;
        }
        else
        {
            lastShotWasHeadShot = false;
            life -= hp;
        }

        lastGunToShoot = gun;

        if (life > 0)
            GetComponent<Animator>().SetTrigger("gotHurt");
    }

    // Use this for initialization
    void Start()
    {
        player = GameObject.Find("FPSController");
        scoreController = GameObject.Find("ScoreController").GetComponent<ScoreController>();
    }

    // Update is called once per frame
    void LateUpdate()
    {
        if (this.isDead)
            return;

        if (life <= 0)
        {
            this.isDead = true;
            if (lastGunToShoot == GunType.Bazooka)
            {
                GetComponent<Animator>().SetBool("explosionKilled", true);
                scoreController.addScore("XPlosion!!!", 500);
            }
            else if (lastShotWasHeadShot)
            {
                GetComponent<Animator>().SetBool("headshotKilled", true);
                scoreController.addScore("Headshot!", 500);
            }
            else
                GetComponent<Animator>().SetBool("normalKilled", true);
            scoreController.addScore("Kill", 250);
        }


        transform.rotation = Quaternion.LookRotation(transform.position - player.transform.position, Vector3.up);
        if ((Time.realtimeSinceStartup - lastShot) > firingDelay)
        {
            lastShot = Time.realtimeSinceStartup;
            this.gameObject.GetComponentInChildren<Gun>().fire();
        }

    }

    public void endDeathAnimation()
    {
        this.gameObject.SetActive(false);
    }

    public void playHurtSound()
    {
        GetComponent<AudioSource>().clip = hurtSound;
        GetComponent<AudioSource>().Play();
    }

    public void playDeathSound()
    {
        GetComponent<AudioSource>().clip = deathSound;
        GetComponent<AudioSource>().Play();
    }

    public void explodeHeadParticle()
    {
        Transform headExplosion = transform.Find("ExplosionHead");
        headExplosion.GetComponent<ParticleSystem>().Play();
        headExplosion.GetComponent<AudioSource>().Play();
        playDeathSound();
    }

    public void explodeBodyParticle()
    {
        Transform bodyExplosion = transform.Find("ExplosionParticle");
        bodyExplosion.GetComponent<ParticleSystem>().Play();
        bodyExplosion.GetComponent<AudioSource>().Play();
        playDeathSound();
    }
}
