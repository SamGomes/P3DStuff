using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour {

    public int life;
    public int armor;

    public string changeGunKeyName;
    public float pickupMargin;

    private int currentGunIndex;
    private List<GameObject> inventory;
    private List<GameObject> allGuns;

    public List<GameObject> getInventory() {
        return inventory;
    }

    public int getCurrentGun() {
        return currentGunIndex;
    }


    public void injure(int hp)
    {
        life -= hp;
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
        //gun.transform.rotation = transform.rotation;
        gun.transform.rotation = transform.rotation;
        gun.transform.Rotate(new Vector3(-90, 0, 90));
        gun.transform.position = transform.position + transform.forward*4 + transform.up*-2;
        gun.transform.parent = transform; //set gun as child of player     
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

        if (life <= 0)
        {
           SceneManager.LoadScene("StartMenu");
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
                (inventory[currentGunIndex].GetComponent<Gun>()).fire();
            }

        }

 


        foreach (GameObject gun in allGuns.ToArray()){ 
            if( !gun.GetComponent<Gun>().picked &&((gun.transform.position - transform.position).magnitude < pickupMargin))
            {
                foreach(GameObject invGun in inventory)
                {
                    if(gun!=invGun && gun.GetComponent<Gun>().gunType == invGun.GetComponent<Gun>().gunType)
                    {
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
