using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WeaponInfoGUI : MonoBehaviour
{
    public Image selectWeaponsPanel = null;

    void changeWeaponType(int weaponNumber)
    {
        float targetPosition = 0.0f;
        switch (weaponNumber)
        {
            case 1:
                targetPosition = 164.0f;
                break;

            case 2:
                targetPosition = 122.0f;
                break;

            case 3:
                targetPosition = 80.0f;
                break;
        }
        Vector3 oldPosition = selectWeaponsPanel.rectTransform.position;
        selectWeaponsPanel.rectTransform.position = new Vector3(oldPosition.x, targetPosition, oldPosition.z);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            changeWeaponType(1);
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            changeWeaponType(2);
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            changeWeaponType(3);
        }
    }

}
