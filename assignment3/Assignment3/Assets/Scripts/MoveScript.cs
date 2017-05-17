using UnityEngine;
using System;

public class MoveScript : MonoBehaviour
{
    public int speed;
    public GameObject playerMesh;
    
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        playerMesh.transform.position = transform.position;
        playerMesh.transform.Rotate(0, Input.GetAxis("Mouse X") * 2, 0);
        float yComponent = Mathf.Deg2Rad * playerMesh.transform.rotation.eulerAngles.y;
        Vector3 movement = new Vector3(moveVertical * Mathf.Sin(yComponent) + moveHorizontal * Mathf.Cos(yComponent), 0.0f, moveVertical * Mathf.Cos(yComponent) + moveHorizontal * Mathf.Sin(yComponent));

        //movement.y= movement.magnitude* Mathf.Sin(Time.deltaTime);

        GetComponent<Rigidbody>().AddForce(movement * speed * Time.deltaTime);
    }

}