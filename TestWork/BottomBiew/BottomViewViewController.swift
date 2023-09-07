//
//  BottomViewViewController.swift
//  TestWork
//
//  Created by Илья Холопов on 07.09.2023.
//

import UIKit

class BottomViewViewController: UIViewController {
    
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var avatarImage: UIImageView!
    @IBOutlet weak var dateLabel: UILabel!
    @IBOutlet weak var timeLabel: UILabel!
    @IBOutlet weak var showHistoryButton: UIButton!
    
    var user: User?
    
    @IBAction func swipeDownView(_ sender: UISwipeGestureRecognizer) {
        UIView.animate(withDuration: 0.3) {
            self.view.frame = CGRect(x: 0.0,
                                     y: self.view.frame.minY + 150,
                                     width: self.view.frame.width, height: 150.0)
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
    }
    
    private func setupView() {
        avatarImage.image = UIImage(systemName: "person.circle.fill")?.withTintColor(.white, renderingMode: .alwaysOriginal)
        avatarImage.backgroundColor = .blue
        avatarImage.layer.borderColor = UIColor.blue.cgColor
        avatarImage.layer.borderWidth = 3.0
        avatarImage.layer.cornerRadius = avatarImage.frame.width / 2
        avatarImage.contentMode = .scaleAspectFill
        self.view.layer.cornerRadius = 15.0
        showHistoryButton.layer.cornerRadius = 15.0
    }
    
    func updateUser(selectUser: User) {
        titleLabel.text = selectUser.name
        if selectUser.avatarImage != nil {
            avatarImage.image = UIImage(named: selectUser.avatarImage!)
        } else {
            avatarImage.image = UIImage(systemName: "person.circle.fill")?.withTintColor(.white, renderingMode: .alwaysOriginal)
        }
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "dd.MM.yyyy"
        dateLabel.text = dateFormatter.string(from: selectUser.date ?? Date())
        
        dateFormatter.dateFormat = "HH:mm"
        timeLabel.text = dateFormatter.string(from: selectUser.date ?? Date())
    }
    
    

}
