using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WeaponInfoGUI : MonoBehaviour {
    public Image selectWeaponsPanel = null;

    void Start()
    {
        changeWeaponType(3);
        Debug.Log("Hello");
    }


    IEnumerator test()
    {
        Debug.Log("Changing Weapon 1");
        changeWeaponType(1);
        yield return new WaitForSeconds(10);
        Debug.Log("Changing Weapon 2");
        changeWeaponType(2);
        yield return new WaitForSeconds(10);
        Debug.Log("Changing Weapon 3");
        changeWeaponType(3);
    }

    void changeWeaponType(int weaponNumber) {
        float targetPosition = 0.0f;
        switch(weaponNumber){
            case 1:
                targetPosition = -42.0f;
                break;

            case 2:
                targetPosition = 0.0f;
                break;

            case 3:
                targetPosition = 42.0f;
                break;
        }
        Vector3 oldPosition = selectWeaponsPanel.rectTransform.position;
        selectWeaponsPanel.rectTransform.position.Set(oldPosition.x, targetPosition, oldPosition.z);
    }

}
