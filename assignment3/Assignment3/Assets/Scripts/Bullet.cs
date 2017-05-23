using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    public float bulletSpeed;
    public float maxBulletTime;

    void Start()
    {
        Destroy(gameObject, maxBulletTime);
    }

    void Update()
    {
        transform.Translate(new Vector3(0, -bulletSpeed, 0) * Time.deltaTime);   
    }
}
