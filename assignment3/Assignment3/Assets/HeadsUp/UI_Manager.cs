using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

class ScoreEntry { 
    public string message;
    public int  addedScore;
}

public class UI_Manager : MonoBehaviour
{
    public Image selectWeaponsPanel = null;
    public Text pistolText = null;
    public Text machineGunText = null;
    public Text bazookaText = null;
    public Image pistolImage = null;
    public Image machineGunImage = null;
    public Image bazookaImage = null;
    public Text armorText = null;
    public Text lifeText = null;
    private Player player;

    public Text scoreText;
    private List<ScoreEntry> scores = new List<ScoreEntry>();
    private ScorePanel scorePanel;
    private int currentScore = 0;

    void Start() {
        GameObject firstPersonCharacter = GameObject.Find("FirstPersonCharacter");
        this.player = firstPersonCharacter.GetComponent<Player>();
            
        pistolImage.enabled = false;
        machineGunImage.enabled = false;
        bazookaImage.enabled = false;

        scorePanel = transform.Find("ScorePanel").GetComponent<ScorePanel>();
        GameObject.Find("ScoreController").GetComponent<ScoreController>().setUI_ManagerAndReset(this);
    }

    public void addScore(string message, int addedScore) {
        scores.Add(new ScoreEntry() { message = message, addedScore = addedScore});

        if (!scorePanel.GetComponent<Animator>().GetBool("newScore")) {
            startScoreAnimation();
        }

    }

    public void startScoreAnimation() {
        if (scores.Count <= 0)
            return;

        int reps = 1;
        ScoreEntry finalScore = scores[0];
        if (scores.Count > 1) {
            for (int i = 1; i < scores.Count; i++) {
                if (finalScore.message.Equals(scores[i].message)) {
                    reps++;
                    finalScore.addedScore += scores[i].addedScore;
                    scores.RemoveAt(i);
                    i--;
                }

            }
        }

        if (reps > 1) {
            finalScore.message = finalScore.message + " x" + reps;
        }
        
        scorePanel.newScoreText.text = finalScore.message;
        scorePanel.newScoreScore.text = "+ " + finalScore.addedScore;
        scorePanel.GetComponent<Animator>().SetBool("newScore", true);
        GetComponent<AudioSource>().Play();
    }

    public void endScoreAnimation() {
        currentScore += scores[0].addedScore;
        scoreText.text = "" + currentScore;
        scores.RemoveAt(0);

        if (scores.Count > 0)
            startScoreAnimation();
        else {
            scorePanel.GetComponent<Animator>().SetBool("newScore", false);
        }
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

        armorText.text = "" + player.armor;
        lifeText.text = "" +player.life;


        //quadractic interpolation
        float x = (float)player.armor / 100.0f;
        x = -(1 - x) * (1 - x) + 1;

        lifeText.color = new Color(1 - x, 0f, 0f);

        armorText.color = new Color(1 - x, 0f, 0f);

        //quadractic interpolation
        x = (float)player.life / 100.0f;
        x = -(1 - x) * (1 - x) + 1;

        lifeText.color = new Color(1 - x, 0f, 0f);

    }

}
