using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Portal : MonoBehaviour {

    public string levelName;
    public GameObject gameCharacter;

    void OnTriggerEnter(Collider other)
    {

        if (other.gameObject == gameCharacter)
        {
            SceneManager.LoadScene(levelName);
        }
    }
}
