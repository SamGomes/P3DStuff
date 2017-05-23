using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WeaponInfoGUI : MonoBehaviour
{
    public Image selectWeaponsPanel = null;
    public Text pistolText = null;
    public Text machineGunText = null;
    public Text bazookaText = null;
    public Image pistolImage = null;
    public Image machineGunImage = null;
    public Image bazookaImage = null;
    private Player player;

    void Start() {
        GameObject firstPersonCharacter = GameObject.Find("FirstPersonCharacter");
        this.player = firstPersonCharacter.GetComponent<Player>();
            
        pistolImage.enabled = false;
        machineGunImage.enabled = false;
        bazookaImage.enabled = false;
    }

    void changeWeaponType(GunType weaponType)
    {
        float targetPosition = 0.0f;
        switch (weaponType)
        {
            case GunType.Pistol:
                targetPosition = 164.0f;
                break;

            case GunType.MachineGun:
                targetPosition = 122.0f;
                break;

            case GunType.Bazooka:
                targetPosition = 80.0f;
                break;
        }
        Vector3 oldPosition = selectWeaponsPanel.rectTransform.position;
        selectWeaponsPanel.rectTransform.position = new Vector3(oldPosition.x, targetPosition, oldPosition.z);
    }

    void setWeaponAmmoCount(Text targetText, Gun gun) {
        targetText.text = gun.getNumberOfBullets() + "/" + gun.maxNumberOfBullets;

        //Quadractic interpolation of number of bullets
        float x = (float)gun.getNumberOfBullets() / gun.maxNumberOfBullets;
        x = -(1 - x)*(1-x) + 1;

        targetText.color = new Color(1-x, 0f, 0f);
    }

    void OnGUI()
    {
        List<GameObject> inventory = player.getInventory();


        //changing current gun
        if (inventory.Capacity != 0)
        {
            selectWeaponsPanel.enabled = true;
            int currentGunIndex = player.getCurrentGun();
            Gun currentGun = inventory[currentGunIndex].GetComponent<Gun>();
            changeWeaponType(currentGun.gunType);
        }
        else {
            selectWeaponsPanel.enabled = false;
        }
     

        foreach (GameObject gameObject in inventory){
            Gun gun = gameObject.GetComponent<Gun>();
            switch (gun.gunType) {
                case GunType.Pistol:
                    pistolImage.enabled = true;
                    setWeaponAmmoCount(pistolText, gun);
                    break;
                case GunType.MachineGun:
                    machineGunImage.enabled = true;
                    setWeaponAmmoCount(machineGunText, gun);
                    break;
                case GunType.Bazooka:
                    bazookaImage.enabled = true;
                    setWeaponAmmoCount(bazookaText, gun);
                    break;

            }
        }

    }

}
