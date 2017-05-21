using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    public float bulletSpeed;

   
    void Update()
    {
        transform.Translate(new Vector3(0, -bulletSpeed, 0) * Time.deltaTime);      
    }
}
