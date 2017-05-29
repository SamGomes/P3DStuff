using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

using UnityStandardAssets.Characters.FirstPerson;

public class Player : MonoBehaviour
{
    public AudioClip playerHit;
    public AudioClip armorHit;
    public AudioClip playerDeath;

    public int life;
    public int armor;

    public string changeGunKeyName;
    public float pickupMargin;

    private int currentGunIndex;
    private List<GameObject> inventory;
    private List<GameObject> allGuns;

    private bool isDead = false;

    public List<GameObject> getInventory() {
        return inventory;
    }

    public int getCurrentGun() {
        return currentGunIndex;
    }

    public void endLevel()
    {
        SceneManager.LoadScene("EndMenu");
    }

    public void injure(int hp)
    {
        if (isDead)
            return;

        if (armor > 0)
        {
            GetComponent<AudioSource>().clip = armorHit;
            armor -= hp;
            if (armor < 0)
                armor = 0;
        }
        else
        {
            GetComponent<AudioSource>().clip = playerHit;
            life -= hp;
        }


        if (life > 0)
        {
            GetComponent<Animator>().SetTrigger("isHurt");
            GetComponent<AudioSource>().Play();
        }
    }

    private void addToInventory(GameObject obj)
    {
        if (!inventory.Contains(obj))
        {
            inventory.Add(obj);
            currentGunIndex = inventory.Count - 1;
            allGuns.Remove(obj);
            setCurrentGun(obj);
        }
    }

    private void setCurrentGun(GameObject gun)
    {
        (gun.GetComponent<Gun>()).picked = true;
        foreach (GameObject invGun in inventory.ToArray())
        {
            if (!invGun.Equals(gun))
            {
                invGun.SetActive(false);
            }
        }

        Transform child = transform.GetChild(0);

        gun.transform.rotation = child.rotation;
        gun.transform.Rotate(new Vector3(-90, 0, 90));
        gun.transform.position = child.position + child.forward*4 + child.up*-2;
        gun.transform.parent = child; //set gun as child of player     
        gun.SetActive(true);
    }

    // Use this for initialization
    void Start() {
        life = 100;
        allGuns = new List<GameObject>();
        inventory = new List<GameObject>();
        currentGunIndex = 0;
        allGuns.AddRange(GameObject.FindGameObjectsWithTag("gun"));
    }
	// Update is called once per frame
	void Update () {
        if (isDead)
            return;

        if (life <= 0)
        {
            life = 0;
            isDead = true;
            GetComponent<AudioSource>().clip = playerDeath;
            GetComponent<AudioSource>().Play();
            GetComponent<Animator>().SetTrigger("isDead");

            //disable controls and physics
            transform.parent.GetComponent<FirstPersonController>().enabled = false;
            transform.parent.GetComponent<CharacterController>().enabled = false;
            //transform.parent.GetComponent<Rigidbody>().isKinematic = true;
        }

        if (inventory.Count > 0)
        {
            if (Input.GetAxis("Mouse ScrollWheel") > 0)
            {
                currentGunIndex = (currentGunIndex + 1) % inventory.Count;
                setCurrentGun(inventory[currentGunIndex]);
            }

            if (Input.GetAxis("Mouse ScrollWheel") < 0)
            {
                currentGunIndex = (currentGunIndex == 0 ? (inventory.Count - 1) : currentGunIndex - 1);
                setCurrentGun(inventory[currentGunIndex]);
            }

            if (Input.GetMouseButton(0))
            {
                (inventory[currentGunIndex].GetComponent<Gun>()).fire(GetComponent<CapsuleCollider>());
            }

        }

 


        foreach (GameObject gun in allGuns.ToArray()){ 
            if( !gun.GetComponent<Gun>().picked &&((gun.transform.position - transform.position).magnitude < pickupMargin))
            {
                foreach(GameObject invGun in inventory)
                {
                    if(gun!=invGun && gun.GetComponent<Gun>().gunType == invGun.GetComponent<Gun>().gunType)
                    {
                        if (invGun.GetComponent<Gun>().hasFullClip())
                            return;
                        invGun.GetComponent<Gun>().addBullets(gun.GetComponent<Gun>().numberOfPickupBullets);
                        inventory[currentGunIndex].GetComponent<Gun>().onPickup();
                        allGuns.Remove(gun);
                        Destroy(gun);
                        return;
                    }
                } 
                addToInventory(gun);
                gun.GetComponent<Gun>().onPickup();
            }
        }

        
    }
}
